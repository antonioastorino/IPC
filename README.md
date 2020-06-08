# IPC
## Inter-process communication
(Documentation under construction. Please, be patient)

*IPC* implements a messaging system between two instances of the same applications.

*IPC* depends on *HEG* **([Huffman's Encoding Generator](https://github.com/antonioastorino/HEG))**.

## How to build and run

```
https://github.com/antonioastorino/HEG.git   # clone HEG
https://github.com/antonioastorino/IPC.git   # clone IPC
cd IPC/project                               # cd to the project folder
./makeMakefile.sh                            # generate Makefile                        
make [OPT=<OPT_LEVEL>]                       # build with desired optimization level
```
`<OPT_LEVEL> = 0, 1, 2, or 3` is the compiler optimization level. If not specified, it will be set equal to `0` by default.

Now you can use the current terminal window for one user. You then need to open another terminal window for the second user. From both windows, make sure you are in `IPC/project/` and run

```
./chat-out-<OPT_LEVEL>
```
Enjoy chatting with yourself!

Once you are done, terminate the communication by sending **from both windows** the character `\`. This will terminate the communication and free the shared memory used to implement it.

## How it works
### General description
The communication between the two windows occurs through a shared buffer. The buffer is identified by an ID (`shmid`). The first instance creates 2 shared buffers, one for transmitting and one for receiving messages. The two `shmid`'s are saved in a file called `shm-id`. The second instance of the app will read `shm-id` and use the saved ID's in inverted order. The file is erased when either application terminates.

The application itself has two child threads:

- **transmitter**, which writes on one buffer
- **receiver**, which reads from the other buffer

Because of the perfect symmetry of the communication system, I will describe the implementation and use of one buffer only

### Shared circular buffer
The shared buffer has a fixed length stored in `IPC::bufferSize` variable, initialized in `IPCCommon.hpp`. It is used as a *circular buffer*.

Let `w` and `r` be the indices at which the transmitter and receiver, respectively, are currently accessing the buffer. The values of `w` and `r` are stored in the last two buffer elements. This implies that, if the buffer is a vector of 8-bit bytes, the buffer cannot be larger than 258 elements, otherwise it would not be possible for the last two elements to contain the required information.

Initially, `w = r = 0` and the transmitter is waiting for inputs from the terminal.
#### Transmitter behavior
Every time the buffer at position `w` is updated by the transmitter, `w` is incremented (and reset when exceeding the buffer size) unless its position is `r - 1`. This means that the receiver has not read the buffer yet and the transmitted has made a full circle around the buffer and "hit" the receiver from behind.
#### Receiver behavior
Every time the buffer at position `r` is read by the receiver, `r` is incremented (and reset when exceeding the buffer size) unless its position is `w`. This means that the receiver read all the messages sent by the transmitter and has to wait.

