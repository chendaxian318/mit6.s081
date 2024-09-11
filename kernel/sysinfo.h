struct sysinfo {
  uint64 freemem;   // amount of free memory (bytes) 空闲内存字节数
  uint64 nproc;     // number of process   state不为UNUSED的线程数
};
