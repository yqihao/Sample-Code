CC = g++
CFLAGS =
COPTFLAGS = -O3 -g
LDFLAGS =

default:
	@echo "=================================================="
	@echo "To build your sorting code, use:"
	@echo "  make hashchain/hash
	@echo "  make mst
	@echo ""
	@echo "To clean this subdirectory (remove object files"
	@echo "and other junk), use:"
	@echo "  make clean"
	@echo "=================================================="

hashchian: hashchian.o
	$(CC) $(COPTFLAGS) -o $@ $^
	
hash: hash.o
	$(CC) $(COPTFLAGS) -o $@ $^

mst: mst.o
	$(CC) $(COPTFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ -c $<

clean:
	rm -f core *.o *~ insertion-sort mergesort

# eof