TARGET=projectplan

all: latex

latex:
	latex $(TARGET).tex 
	-bibtex $(TARGET)
	latex $(TARGET).tex
	latex $(TARGET).tex
	dvipdf $(TARGET).dvi
clean:
	-rm -f $(TARGET).aux
	-rm -f $(TARGET).toc
	-rm -f $(TARGET).out
	-rm -f $(TARGET).snm
	-rm -f $(TARGET).nav
	-rm -f $(TARGET).bbl
	-rm -f $(TARGET).blg
	-rm -f $(TARGET).log
	-rm -f $(TARGET).dvi
	-rm -f $(TARGET)-blx.bib
	-rm -f $(TARGET).run.xml
	-rm -f texput.log
