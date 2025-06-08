`get-next-line` acts as a smart wrapper around the basic read() syscall. <br>
<br>
It adds the logic to:
* Identify line breaks
* Buffer leftover data
* Return one complete line at a time
