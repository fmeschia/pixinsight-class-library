#!/bin/bash

BASEDIR=$PCLSRCDIR/modules/processes

# cd $BASEDIR/BackgroundModelization/$PCLHOST/g++
# make -j$(nproc)

cd $BASEDIR/CloneStamp/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/ColorCalibration/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/ColorManagement/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/ColorSpaces/$PCLHOST/g++
make -j$(nproc)

# cd $BASEDIR/Compatibility/$PCLHOST/g++
# make -j$(nproc)

cd $BASEDIR/Convolution/$PCLHOST/g++
make -j$(nproc)

# cd $BASEDIR/Deconvolution/$PCLHOST/g++
# make -j$(nproc)

cd $BASEDIR/Flux/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/Fourier/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/GaiaDR2/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/Geometry/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/Global/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/GREYCstoration/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/Image/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/ImageCalibration/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/ImageIntegration/$PCLHOST/g++
make -j$(nproc)

# cd $BASEDIR/ImageRegistration/$PCLHOST/g++
# make -j$(nproc)

cd $BASEDIR/IntensityTransformations/$PCLHOST/g++
make -j$(nproc)

# cd $BASEDIR/MaskGeneration/$PCLHOST/g++
# make -j$(nproc)

cd $BASEDIR/Morphology/$PCLHOST/g++
make -j$(nproc)

# cd $BASEDIR/MultiscaleProcessing/$PCLHOST/g++
# make -j$(nproc)

cd $BASEDIR/NoiseGeneration/$PCLHOST/g++
make -j$(nproc)

# cd $BASEDIR/NoiseReduction/$PCLHOST/g++
# make -j$(nproc)

cd $BASEDIR/NoOperation/$PCLHOST/g++
make -j$(nproc)

# cd $BASEDIR/Obsolete/$PCLHOST/g++
# make -j$(nproc)

cd $BASEDIR/PixelMath/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/RestorationFilters/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/Sandbox/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/StarGenerator/$PCLHOST/g++
make -j$(nproc)

# cd $BASEDIR/TGV/$PCLHOST/g++
# make -j$(nproc)

cd $BASEDIR/contrib/cleger/SubframeSelector/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/contrib/gviehoever/GradientDomain/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/contrib/kkretzschmar/INDIClient/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/contrib/nmisiura/StarNet/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/contrib/nvolkov/Blink/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/contrib/nvolkov/CometAlignment/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/contrib/nvolkov/CosmeticCorrection/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/contrib/nvolkov/SplitCFA/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/contrib/sharkmelley/ArcsinhStretch/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/contrib/spool/Debayer/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/contrib/zvrastil/Annotation/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/contrib/zvrastil/AssistedColorCalibration/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR/contrib/zvrastil/LocalHistogramEqualization/$PCLHOST/g++
make -j$(nproc)

cd $BASEDIR