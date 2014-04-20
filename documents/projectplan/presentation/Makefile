TARGET=projectplan

all: latex

latex:
	latex $(TARGET).tex 
	-bibtex $(TARGET)
	latex $(TARGET).tex
	latex $(TARGET).tex
	dvipdf $(TARGET).dvi

clean:
	-rm $(TARGET).aux
	-rm $(TARGET).toc
	-rm $(TARGET).out
	-rm $(TARGET).snm
	-rm $(TARGET).nav
	-rm $(TARGET).bbl
	-rm $(TARGET).blg
	-rm $(TARGET).log
	-rm $(TARGET).dvi
	-rm $(TARGET)-blx.bib
	-rm $(TARGET).run.xml
	-rm texput.log
