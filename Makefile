all:
	mkdir target
	cd src/librts4-201602111900 && $(MAKE)
	cd src/libcdk13-201802181144 && $(MAKE)
	cd src/gr8 && $(MAKE)

clean:
	cd gr8 && $(MAKE) clean
	rm -r target
