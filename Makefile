CC := g++
CFLAGS := -std=c++17 -Wall -Wextra -Werror

SRCS := sync.cpp
OBJS := $(SRCS:.cpp=.o)
EXEC := sync_folders

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)