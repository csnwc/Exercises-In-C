all : ../exercisesInC.pdf

../exercisesInC.pdf : *.tex
	pdflatex exercisesInC.tex
	pdflatex exercisesInC.tex
	rm -f ../exercisesInC.pdf
	cp exercisesInC.pdf ..
	rm -f *.log *.ptc *.toc *.run.xml *.bcf *.out *.aux *.idx ./exercisesInC.pdf

clean:
	rm -f *.log *.ptc *.toc *.run.xml *.bcf *.out *.aux *.idx ./exercisesInC.pdf


quicky:
	pdflatex exercisesInC.tex
