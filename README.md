# SyslogPerf
Measures syslog performance, https://superuser.com/questions/305029/why-is-syslog-so-much-slower-than-file-io

```
> ./syslog_perf
Test Case             Calls       Payload     Duration    Thoughput 
                      []          [MB]        [s]         [MB/s]    
--------------------  ----------  ----------  ----------  ----------
syslog                200000      10.00       46.74       0.21      
syslog %s             200000      10.00       47.01       0.21      
write /dev/null       200000      10.00       0.05        191.72    
printf %s             200000      10.00       0.01        894.69
```
