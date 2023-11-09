JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java



CLASSES = \
	Buffer.java \
	Consumer.java \
	Coordinator.java \
	Generator.java

default: classes

classes: $(CLASSES:.java=.class)
clean:
	$(RM) *.class *.tar
tar:
	tar -cvzf Ojaswi-Sinha-HW5.tar *.java *.txt Makefile
