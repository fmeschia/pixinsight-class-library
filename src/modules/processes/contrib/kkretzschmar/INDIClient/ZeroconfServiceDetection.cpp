#include <errno.h>            // For errno, EINTR #include <time.h>
#ifdef _WIN32
#include <process.h>
typedef    int    pid_t;
#define    getpid    _getpid
#define    strcasecmp    _stricmp
#define snprintf _snprintf
#else
#include <sys/time.h>        // For struct timeval
#include <arpa/inet.h>       // For inet_addr(  )
#include <net/if.h>          // for interface name family functions
#include <sys/types.h>       // for ifaddr struct
#include <ifaddrs.h>         // for getifaddr function
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <linux/wireless.h>
#include <sys/ioctl.h>
#endif

#include "ZeroconfServiceDetection.h"
#include "INDIClient.h"
#include <pcl/Console.h>
#include <pcl/MetaModule.h>

#define LONG_TIME 100000000

namespace pcl {


#ifdef WITH_ZEROCONF
void ZeroConfServiceHandler::Run()
{
  
  int dns_sd_fd = DNSServiceRefSockFD(m_serviceRef);
  int nfds = dns_sd_fd + 1;
  fd_set readfds;
  struct timeval tv;
  int result;
  m_stop = false;
  static volatile int timeOut = LONG_TIME;
  while (!m_stop) {
    Module->ProcessEvents();
    FD_ZERO(&readfds);
    FD_SET(dns_sd_fd, &readfds);
    tv.tv_sec = timeOut;
    tv.tv_usec = 0;
    result = select(nfds, &readfds, (fd_set*)NULL, (fd_set*)NULL, &tv);
    if (result > 0)
      {
        DNSServiceErrorType err = kDNSServiceErr_NoError;
        if (FD_ISSET(dns_sd_fd, &readfds))    err = DNSServiceProcessResult(m_serviceRef);
        if (err) m_stop = true;
      }
    else
      {
        Console().WriteLn(String().Format("select(  ) returned %d errno %d %s",result, errno, strerror(errno)));
        if (errno != EINTR) m_stop = true;
      }
    }
  
}

bool ZeroConfServiceHandler::getAddrInfoFromInterfaceIndex(uint32_t interfaceIndex, char* host)
{
  char* ifNameBuff = static_cast<char*>(malloc(IF_NAMESIZE));
  if_indextoname(interfaceIndex, ifNameBuff);

  struct ifaddrs *ifaddr, *ifa;
  int family, s;

  if (getifaddrs(&ifaddr) == -1)
  {
     return false;
  }

  /* Walk through linked list, maintaining head pointer so we
     can free list later */

  for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
  {
      if (ifa->ifa_addr == NULL)
        continue;

      if (strcmp(ifa->ifa_name, ifNameBuff) != 0)
        continue;

      family = ifa->ifa_addr->sa_family;


      /* For an AF_INET* interface address, display the address */
      // only IP v4 supported yet
      if (family == AF_INET ) {
           s = getnameinfo(ifa->ifa_addr,sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
           if (s != 0)
           {
             freeifaddrs(ifaddr);
             return false;
           } else
           {
             freeifaddrs(ifaddr);
             return true;
           }
       }
   }

  freeifaddrs(ifaddr);
  return false;
}

bool ZeroConfServiceHandler::isWireless(const IsoString& interfaceName)
{
  int sock = -1;
  struct iwreq pwrq;
  memset(&pwrq, 0, sizeof(pwrq));
  strncpy(pwrq.ifr_name, interfaceName.c_str(), IFNAMSIZ);

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    return false;
  }

  if (ioctl(sock, SIOCGIWNAME, &pwrq) != -1) {
    close(sock);
    return true;
  }

  close(sock);
  return false;
}

void ZeroConfServiceBrowser::Start()
{
  DNSServiceErrorType error;
  error = DNSServiceBrowse(&m_serviceRef,
                          0,                // no flags
                          0,                // all network interfaces
                          "_indigo._tcp",     // service type
                          "",               // default domains
                          ZeroConfServiceBrowser::onBrowseEvent, // call back function
                          static_cast<void*>(m_client.get()));
  if (error == kDNSServiceErr_NoError)
  {
    Thread::Start(); // Start thread and add the service to the runloop to get callback calls
  }
  else
  {
    Console().WriteLn(String().Format("DNSServiceBrowse(...) returned %d s", error));
  }
}



void ZeroConfServiceBrowser::onBrowseEvent(DNSServiceRef service,
                                           DNSServiceFlags flags,
                                           uint32_t interfaceIndex,
                                           DNSServiceErrorType errorCode,
                                           const char * name,
                                           const char * type,
                                           const char * domain,
                                           void * context)
{
 
  if (errorCode != kDNSServiceErr_NoError)
    Console().WriteLn(String().Format("MyBrowseCallBack returned %d", errorCode));
  else
  {
    char* host = static_cast<char*>(malloc(NI_MAXHOST));
    char* ifNameBuff = static_cast<char*>(malloc(IF_NAMESIZE));
    if_indextoname(interfaceIndex, ifNameBuff);
    
    ZeroConfClient* client = static_cast<ZeroConfClient*>(context);
    if (client == nullptr)
      return;
    bool startResolver = false;
    {
      
      ExclZeroConfServicesList y = client->ZeroConfServicesList();
      ZeroConfServicesArray& services(y);
      ZeroConfServiceItem item(name, type, domain, interfaceIndex);
      if (!services.Contains(item) && (flags & kDNSServiceFlagsAdd))
      {
        client->onServiceAdded(item);
         
        if (!ZeroConfServiceHandler::getAddrInfoFromInterfaceIndex(interfaceIndex, host))
        {
          Console().WarningLn(String().Format("Call of getAddrInfoFromInterfaceIndex failed."));
        }
        item.InterfaceName = IsoString(ifNameBuff);
        item.IsWireless = isWireless(item.InterfaceName.c_str());
        services << item;
        Console().WriteLn("");
        Console().WriteLn(String().Format("Indigo service added on network interface '%s' with address '%s'", ifNameBuff, host));
 
        startResolver = true;
        
      } 
      else if (services.Contains(item) && !(flags & kDNSServiceFlagsAdd))
      {
        client->onServiceRemoved(item);
        
       // remove service from service list
        services.Remove(item);
        Console().WriteLn("");
        Console().WriteLn(String().Format("Indigo service removed on network interface '%s'", ifNameBuff));
      }
    }
    if (startResolver)
    {
      ZeroConfServiceResolver resolver(*client, name, type, domain, interfaceIndex);
      resolver.Start(); // creates a new client and a new connection
    }
  }

  //if (!(flags & kDNSServiceFlagsMoreComing)) fflush(stdout);
}

void ZeroConfServiceResolver::onResolveEvent(DNSServiceRef serviceRef,
                                             DNSServiceFlags flags,
                                             uint32_t interface,
                                             DNSServiceErrorType errorCode,
                                             const char *fullname,
                                             const char *hosttarget,
                                             uint16_t port,
                                             uint16_t txtLen,
                                             const unsigned char *txtRecord,
                                             void *context)
{

  ResolveContext* resolveContext = static_cast<ResolveContext*>(context);
  if (resolveContext == nullptr || resolveContext->m_zeroConfServiceResolver == nullptr)
    return;
  if (errorCode != kDNSServiceErr_NoError)
  {
    Console().CriticalLn(String().Format("Zeroconf resolve callback returned %d", errorCode));
  }
  else
  {

    // Update information in service ZeroConfServicesArray
    ExclZeroConfServicesList y = resolveContext->m_zeroConfClient.ZeroConfServicesList();
    ZeroConfServicesArray& services(y);
    ZeroConfServiceItem item(resolveContext->m_zeroConfServiceResolver->m_serviceName, resolveContext->m_zeroConfServiceResolver->m_serviceType , resolveContext->m_zeroConfServiceResolver->m_serviceDomain, resolveContext->m_zeroConfServiceResolver->m_InterfaceIndex);
    auto searchedItem = services.Search(item);
    if (searchedItem != services.End())
    {
      // update entry in list
      ZeroConfServiceItem newItem(*searchedItem);
      services.Remove(searchedItem);
      newItem.Host = IsoString(hosttarget);
      newItem.Port = ntohs(port);
      services.Add(newItem);
    }
    else 
    {
      Console().WarningLn(String("<p>Service not found:</p>"
                                 "<p>name: " + resolveContext->m_zeroConfServiceResolver->m_serviceName + ", type: " + resolveContext->m_zeroConfServiceResolver->m_serviceType + ", domain: " + resolveContext->m_zeroConfServiceResolver->m_serviceDomain + ", index: " + resolveContext->m_zeroConfServiceResolver->m_InterfaceIndex + "</p>"));  
    }

    Console().WriteLn(String().Format("* service name: '%s', service host:  '%s:%d'", fullname, hosttarget, ntohs(port)));
  }
  resolveContext->m_zeroConfServiceResolver->Stop();
}

void ZeroConfServiceResolver::Start()
{
  DNSServiceErrorType error;
  error = DNSServiceResolve(&m_serviceRef,
                            0,                // no flags
                            0,                // all network interfaces
                            m_serviceName.c_str(), // service name as detected by the service browser
                            m_serviceType.c_str(), // service type
                            "",               // default domains
                            ZeroConfServiceResolver::onResolveEvent, // call back function
                            static_cast<void*>(&m_resolveContext));
  if (error == kDNSServiceErr_NoError)
  {
    ZeroConfServiceHandler::Run(); //  add the service to the runloop to get callback calls
  }
  else
  {
    Console().CriticalLn(String().Format("ZeroConfServiceResolver(...) returned %d s", error));
  }
}
#endif // WITH_ZEROCONF
}
