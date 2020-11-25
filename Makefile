all : exercisesInC.pdf

exercisesInC.pdf : 
	cd Tex; pdflatex exercisesInC.tex; pdflatex exercisesInC.tex; mv exercisesInC.pdf ..
	cd Tex; pdflatex exercisesInC.tex; pdflatex exercisesInC.tex; mv exercisesInC.pdf ..

clean:
	rm -fr Tex/exercisesInC.log
	rm -fr Tex/exercisesInC.ptc
	rm -fr Tex/exercisesInC.toc
	rm -fr Tex/exercisesInC.run.xml
	rm -fr Tex/exercisesInC.bcf
	rm -fr Tex/exercisesInC.out
	rm -fr Tex/exercisesInC.aux
	rm -fr Tex/exercisesInC.idx
