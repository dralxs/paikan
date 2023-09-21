# Malware C - Ethical Hacking 

## Introduction 

The malware I am currently trying to make is a rootkit that works on windows system. It is called **Paikan** in reference to the book "La nuit des temps" of René Barjavel.

### Hooking 

The principle of hooking when making a rootkit is to alterate the flow of API calls to use it in 
a malicious way.

For Windows there is various ways to make this happen but I will focus on one : IAT Hooking,
IAT (Import Address Table) contains pointers to :
- DLLs
- function names and addresses for those DLLs

There is PE (portable exacutable) such as commons dlls used on windows (user32.dll), 
that contain this IAT structure.

### Hiding 

[TODO]

## Steps 

### Hooking 

- Make a function that locate the IAT of user32.dll [done]
- Find the address of the function to hook
- Replace the address
- Write a hook function (for example a reverse shell)
- Optional : restoration of the old function address

### Hiding 

[TODO]

