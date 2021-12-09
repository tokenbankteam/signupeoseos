build: wast

clean:
	rm signupeoseos.wast
	rm signupeoseos.wasm

abi:
	eosiocpp -g signupeoseos.abi signupeoseos.hpp -I .

wast:
	eosiocpp -o signupeoseos.wast signupeoseos.cpp -I .

deploy:
	cleos set contract clement12345 ../signupeoseos -p signupeoseos

build_and_deploy: build deploy
