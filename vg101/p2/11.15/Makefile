objects = OneCard.o Log.o Objs.o UI.o
onecard: $(objects)
			gcc -o onecard $(objects)
$(objects) : UI.h	
onecard.o : Defs.h Log.h Objs.h 
Log.o :Defs.h 
Objs.o : Defs.h Log.h Objs.h 
.PHONY : clean
clean:
		-rm onecard $(objects)