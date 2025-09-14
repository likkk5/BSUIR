CC = gcc
CFLAGS = -Wall

all: lab3 
lab3: lab3.c
	$(CC) $(CFLAGS) -o lab3 lab3.c
test: lab3
	./lab3 < test/test_data.txt > test/actual_result.txt; 
	act=$$(cat test/actual_result.txt); \
	exp=$$(cat test/expected_result.txt); \
	if [ "$$act" = "$$exp" ]; then \
	echo "Test passed"; \
	else \
	echo "Test failed"; \
	fi; \
	
clean:
	rm -f lab3