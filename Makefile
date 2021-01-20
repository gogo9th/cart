all: main.cpp helpers.cpp helpers.h classes.h
	g++ -o sku main.cpp helpers.cpp

.PHONY:
clean:
	rm -f sku a
