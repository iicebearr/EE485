CC ?= gcc209
CFLAGS += -g

TARGET := customer_manager1 customer_manager2

all: $(TARGET)

array: customer_manager1

hash: customer_manager2

customer_manager1: client.o customer_manager1.o
	$(CC) $(CFLAGS) -o $@ $^

customer_manager2: client.o customer_manager2.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c $<

clean:
	rm -f $(TARGET) *.o *~

.PHONY: all array hash clean 