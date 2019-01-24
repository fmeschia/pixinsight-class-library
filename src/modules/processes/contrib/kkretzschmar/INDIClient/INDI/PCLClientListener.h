//     ____   ______ __
//    / __ \ / ____// /
//   / /_/ // /    / /
//  / ____// /___ / /___   PixInsight Class Library
// /_/     \____//_____/   PCL 02.01.11.0938
// ----------------------------------------------------------------------------
// Standard INDIClient Process Module Version 01.01.00.0238
// ----------------------------------------------------------------------------
// PCLClientListener.h - Released 2019-01-21T12:06:42Z
// ----------------------------------------------------------------------------
// This file is part of the standard INDIClient PixInsight module.
//
// Copyright (c) 2014-2018 Klaus Kretzschmar
//
// Redistribution and use in both source and binary forms, with or without
// modification, is permitted provided that the following conditions are met:
//
// 1. All redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. All redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// 3. Neither the names "PixInsight" and "Pleiades Astrophoto", nor the names
//    of their contributors, may be used to endorse or promote products derived
//    from this software without specific prior written permission. For written
//    permission, please contact info@pixinsight.com.
//
// 4. All products derived from this software, in any form whatsoever, must
//    reproduce the following acknowledgment in the end-user documentation
//    and/or other materials provided with the product:
//
//    "This product is based on software from the PixInsight project, developed
//    by Pleiades Astrophoto and its contributors (http://pixinsight.com/)."
//
//    Alternatively, if that is where third-party acknowledgments normally
//    appear, this acknowledgment must be reproduced in the product itself.
//
// THIS SOFTWARE IS PROVIDED BY PLEIADES ASTROPHOTO AND ITS CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL PLEIADES ASTROPHOTO OR ITS
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, BUSINESS
// INTERRUPTION; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; AND LOSS OF USE,
// DATA OR PROFITS) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
// ----------------------------------------------------------------------------

#ifndef CLIENTLISTENER_H
#define CLIENTLISTENER_H

#include "baseclient.h"
#include "IClientListener.h"

#include <pcl/Thread.h>
#include <pcl/Exception.h>

namespace INDI {


/* === ICLientListener =====================================================================
 *
 * Interface for the listener of the INDI client.
 *
 * Any listener that is intended to be used in the INDI Client has to implement this
 * interface. The interface abstracts from a specific thread implementation and therefore
 * supports to use different thread implementations, e.g. special thread management
 * frameworks that control the execution of threads on multiprocessor systems.
 *
 ========================================================================================= */

class PclClientListener : public IClientListener, public pcl::Thread {
private:
	// does not own the client
	BaseClient* m_baseClient;
public:
	PclClientListener(BaseClient* baseclient):m_baseClient(baseclient) {}
	virtual ~PclClientListener() {}

	void Run() override {
		try {
			BaseClient::listenHelper(m_baseClient);
		} catch (pcl::ProcessAborted& e) {
			// If a  thread is aborted a Processaborted is thrown and has to be catched here
		}
	}
	void Start() override {
		pcl::Thread::Start();
	}
	void Stop() override {
		pcl::Thread::Abort();
	}
	void Join() override {
		pcl::Thread::Wait();
	}

};

}

#endif // CLIENTLISTENER_H

// ----------------------------------------------------------------------------
// EOF PCLClientListener.h - Released 2019-01-21T12:06:42Z
