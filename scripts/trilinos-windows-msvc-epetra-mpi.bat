cmake -D CMAKE_INSTALL_PREFIX:PATH=c:\Users\dzturne\Software\trilinos_kdice\build_mpi\install -D CMAKE_BUILD_TYPE:STRING=RELEASE -D Trilinos_ASSERT_MISSING_PACKAGES=OFF -D Trilinos_ENABLE_ALL_PACKAGES:BOOL=OFF -D Trilinos_ENABLE_ALL_OPTIONAL_PACKAGES:BOOL=OFF -D Trilinos_ENABLE_ALL_FORWARD_DEP_PACKAGES:BOOL=OFF -D TPL_ENABLE_Pthread:BOOL=OFF -D TPL_ENABLE_Boost:BOOL=ON -DBoost_LIBRARY_DIRS:PATH="C:\Users\dzturne\Software\boost_0_55_0\build_intel\install\lib" -DBoost_INCLUDE_DIRS:PATH="C:\Users\dzturne\Software\boost_1_55_0\build_intel\install\include" -D TPL_ENABLE_MPI:BOOL=ON -DMPI_BASE_DIR:PATH="C:\Program Files (x86)\Microsoft SDKs\MPI" -DCMAKE_INCLUDE_PATH:PATH="C:\Program Files (x86)\Microsoft SDKs\MPI\Include" -D Trilinos_ENABLE_Fortran:BOOL=OFF -D CMAKE_VERBOSE_MAKEFILE:BOOL=FALSE -D Trilinos_ENABLE_TeuchosCore:BOOL=ON -D Trilinos_ENABLE_TeuchosParameterList:BOOL=ON -D Trilinos_ENABLE_TeuchosNumerics:BOOL=ON -D Trilinos_ENABLE_CXX11:BOOL=ON -D Trilinos_ENABLE_Epetra:BOOL=ON  -D Trilinos_ENABLE_OpenMP:BOOL=OFF -D BLAS_LIBRARY_DIRS:PATH="C:\Users\dzturne\Software\clapack\build_intel\BLAS\SRC" -D LAPACK_LIBRARY_DIRS:PATH="C:\Users\dzturne\Software\clapack\build_intel\SRC" -DCMAKE_EXE_LINKER_FLAGS:STRING="C:\Users\dzturne\Software\clapack\build_intel\F2CLIBS\libf2c\libf2c.lib" -G "NMake Makefiles" ..