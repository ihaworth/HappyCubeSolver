CubeSolver:  CubeMain.o CubeInit.o CubeSearch.o CubeCorner.o CubeSim.o \
                CubePrint.o CubeBits.o Small_Cube.o Small_Bar.o Big_Bar.o \
                Big_Cube.o The_Star.o CommonHead.h CubeHeader.h MainHeader.h
              Link -o CubeSolver CubeMain.o CubeInit.o CubeSearch.o \
                CubeCorner.o CubeSim.o CubePrint.o CubeBits.o Small_Cube.o \
                Small_Bar.o Big_Bar.o Big_Cube.o The_Star.o \
                $.RISC_OSLib.o.RISC_OSLib $.Clib.o.stubs
              squeeze CubeSolver
              
CubeMain.o:   CubeMain.c CommonHead.h MainHeader.h
              cc -c -list CubeMain.c -i$.RISC_OSLib
              
CubeInit.o:   CubeInit.c CommonHead.h CubeHeader.h
              cc -c -list CubeInit.c -i$.RISC_OSLib
              
CubeSearch.o: CubeSearch.c CommonHead.h CubeHeader.h
              cc -c -list CubeSearch.c -i$.RISC_OSLib
              
CubeCorner.o: CubeCorner.c CommonHead.h CubeHeader.h
              cc -c -list CubeCorner.c -i$.RISC_OSLib
              
CubeSim.o:    CubeSim.c CommonHead.h CubeHeader.h
              cc -c -list CubeSim.c -i$.RISC_OSLib
              
CubePrint.o:  CubePrint.c CommonHead.h CubeHeader.h
              cc -c -list CubePrint.c -i$.RISC_OSLib
              
CubeBits.o:   CubeBits.c CommonHead.h CubeHeader.h
              cc -c -list CubeBits.c -i$.RISC_OSLib
              
Small_Cube.o: Small_Cube.c CommonHead.h CubeHeader.h
              cc -c -list Small_Cube.c -i$.RISC_OSLib
              
Small_Bar.o:  Small_Bar.c CommonHead.h CubeHeader.h
              cc -c -list Small_Bar.c -i$.RISC_OSLib
               
Big_Bar.o:    Big_Bar.c CommonHead.h CubeHeader.h
              cc -c -list Big_Bar.c -i$.RISC_OSLib
              
Big_Cube.o:   Big_Cube.c CommonHead.h CubeHeader.h
              cc -c -list Big_Cube.c -i$.RISC_OSLib
              
The_Star.o:   The_Star.c CommonHead.h CubeHeader.h
              cc -c -list The_Star.c -i$.RISC_OSLib
              