all : update 

update:
	mkdir -p htmldoc
	LHCfroot -l -q -b thtml_sample.cpp
	cp -rf fig htmldoc/

upload :
	rsync -av -e ssh htmldoc/ lhcf@lhcfs1.stelab.nagoya-u.ac.jp://lhcfs1/www/html/analysis/ClassIndex
#	rsync -av -e ssh htmldoc taccetti@hep:/discone/www/LHCf/Pages/Documents/Temp/menjo/

clean:
	rm -f  *~
	rm -rf htmldoc

