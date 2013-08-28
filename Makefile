CKITGEN = ..\ckit\ckitgen.py
PYTHON  = C:\Python27\python.exe
TCC     = $(USERPROFILE)\app\tcc\tcc.exe
TCCOPTS = -Wall

balles.exe: main.o ckit.o
	$(TCC) $(TCCOPTS) -lOpenGL32 -o $@ $+

main.o: main.c main.h ckit.h
	$(TCC) $(TCCOPTS) -I. -c $<

ckit.o: ckit.c ckit.h
	$(TCC) $(TCCOPTS) -I. -c $<

ckit.c: ckit.config
	$(PYTHON) $(CKITGEN)

