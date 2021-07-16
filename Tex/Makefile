all : exercisesInC.pdf

exercisesInC.pdf : 
	pdflatex exercisesInC.tex
	pdflatex exercisesInC.tex
	mv exercisesInC.pdf ..

clean:
	rm -fr *.log *.ptc *.toc *.run.xml *.bcf *.out *.aux *.idx ./exercisesInC.pdf
