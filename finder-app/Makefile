CC = $(CROSS_COMPILE)gcc

writer: writer.c
	$(CC) -o writer writer.c

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
