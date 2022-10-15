all : exercisesInC.pdf

exercisesInC.pdf : 
	pdflatex exercisesInC.tex
	pdflatex exercisesInC.tex
	rm ../exercisesInC.pdf
	cp exercisesInC.pdf ..
	rm -fr *.log *.ptc *.toc *.run.xml *.bcf *.out *.aux *.idx ./exercisesInC.pdf

clean:
	rm -fr *.log *.ptc *.toc *.run.xml *.bcf *.out *.aux *.idx ./exercisesInC.pdf


quicky:
	pdflatex exercisesInC.tex
