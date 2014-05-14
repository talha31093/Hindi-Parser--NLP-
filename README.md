Hindi-Parser--NLP-
==================

A Top Down Approach to Hindi Parser without using chunker 

HINDI PARSER
Submitted by - Mohammad Talha Khan (IIT2011073)
			   Aaquib Khwaja (IIT2011127)

(A) Requirements -
	Operating System				:	LINUX (tested on Fedora-8 and lower versions)
	Compiler/Interpreter/Librarie(s):	g++, Perl and SSF API's
	
	Note : Use Backtrack OS if possible(No need to do anything to meet the above requirements, all are in built).
	
(B) Basic Installation of Shallow parser (Needed for getting the tagged outputs)
	Follow the below Steps : 

  1)  untar the binary package of shallow-parser-hin-4.0.tgz
		tar -xvzf shallow-parser-hin-4.0.fc8.tgz

  2)  `cd' to the directory containing the package binary.
		cd shallow-parser-hin-4.0

  3.1) Export the Variable `SHALLOW_PARSER_HIN'.
		echo "export SHALLOW_PARSER_HIN=~/sampark/shallow_parser_hin" >> ~/.bashrc

  3.2) Set the PATH to the SHALLOW_PARSER_HIN/bin/sl/sys/hin
		echo "export PATH=\$PATH:\$SHALLOW_PARSER_HIN/bin/sys/hin/" >> ~/.bashrc

  3.3) Compile the ~/.bashrc
		source ~/.bashrc

  4)   To Install 
       Type `make install' to install the programs, data files and documentation.
		make install
	
	NOTE : For any installation issues, refer to actual read me's inside shallow-parser-hin-4.0.fc8 directory, or,
		   contact: 291.khwaja@gmail.com
		            talha31093@gmail.com

(C) To run shallow parser hindi, use the following command in the terminal:
	
	cd /shallow-parser-hin-4.0.fc8
	shallow_parser_hin < INPFILE   > OUTFILE
  
(D) For getting the tagged output file, do the following -
	
	cd /shallow-parser-hin-4.0.fc8/OUTPUT.tmp
	vi postagger.tmp

(E) Run the following shellscript - 
	
	first do the following:
		cd /shallow-parser-hin-4.0.fc8/
		check the path name in tags.cpp
		put the following files in shallow-parser-hin-4.0.fc8 directory -
			tags.cpp
			parse.cpp
			child.cpp
			rules.txt
			parser.sh
		
	./parser.sh
	
	Sample sentence - यह दीर्घ सूत्री कार्य कब तक सम्पूर्ण होगा
	
	(Time taken by few sentences may be a bit long so you may have to wait for a few seconds to a minute to get the output)
	
(F) Contents of parser.sh

	1. shallow_parser_hin < INPFILE > OUTFILE  //  takes the input file(INPFILE), containing a hindi sentence and performs tagging.
	2. c++ tags.cpp  						   //  takes 1 input file postagger.tmp and extracts the tags in the required format.
	3. ./a.out  							   //  generates tag.txt in the required format.
	4. c++ parse.cpp  						   //  takes 2 input files, rules.txt and tag.txt and performs the top-down parsing.
	5. ./a.out  							   //  generates tree.txt (parse tree).
	6. c++ child.cpp  						   //  takes 1 input file, tree.txt and constructs the actual tree with nodes and pointers.
	7. ./a.out  							   //  generates graph.dot (used for generating the tree).
	8. dot -Tpng graph.dot -o graph.png  	   //  creates an image file of the parse tree.
	9. display graph.png 					   //  displays graph.png (actual parse tree).

(G) Files attached -

	1. shallow parser (http://ltrc.iiit.ac.in/showfile.php?filename=downloads/shallow_parser.php) - download the Hindi version
	2. INPFILE
	3. tags.cpp
	4. parse.cpp
	5. child.cpp
	6. rules.txt					 	 	   //  production rules for Hindi Grammar.
	7. parser.sh							   //  shell script to perform all the compiling and running through one command.

(HFor fast and easy Hindi Typing, download Google Input Tools on Windows for Hindi (http://www.google.com/inputtools/windows/)
