.PHONY: greet build run jar run-jar clean 

greet:
	@echo "Terminating make - please specify target explicitly"
	@echo "    build   : compile java program"
	@echo "    run     : run java program using class tree"
	@echo "    jar     : pack java program into an archive for easy distribution"
	@echo "    run-jar : run java program using jar archive"
	@echo "    clean   : perform full clean"

build:
	javac lab3/java/MainClass/main.java

run: build
	java lab3.java.MainClass.main $(N) $(OPT)

jar: build
	jar cvfm main.jar manifest `find . -name "*.class"`

run-jar: jar
	java -jar main.jar $(N) $(OPT)

clean:
	rm -vf *.jar
	find . -name "*.class" -delete -printf "removed '%p'\n"
