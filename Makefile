all:
	cd src/librts4-201602111900 && $(MAKE) install
	cd src/libcdk13-201802181144 && $(MAKE) install
	cd src/gr8 && $(MAKE)
	cp src/gr8/gr8 target/


clean:
	cd src/gr8 && $(MAKE) clean
	cd src/libcdk13-201802181144 && $(MAKE) clean
	find . -type f -name '*.o' -delete
	rm -rf src/libcdk13-201802181144/cdk	
	rm -rf src/libcdk13-201802181144/doc
	rm -rf target
