###########################################################
#
# Simple Makefile for Operating Systems Project 1
# tcush
#
# (C Version)
#
###########################################################
.SUFFIXES: .h .c .l .o

CC = gcc
CFLAGS = -w -g
LEX = flex
LIBS = -lfl -lpthread 
RM = /bin/rm
RMFLAGS = -f

TQ = taskQueue
TQ_OBJS = common.o linkedList.o queue.o taskQueue.o


all: taskQueue

taskQueue: $(TQ_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(RMFLAGS) *.o taskQueue
