all: base64

base64:
	@gcc -o base64.out base64.c

clean:
	@rm base64.out