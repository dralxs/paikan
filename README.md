# Malware C - Ethical Hacking 

## Introduction 

The malware I am currently trying to make is a rootkit that works on windows system. It is called **Paikan** in reference to the book "La nuit des temps" by René Barjavel.
I am not responsible for any misuse of this program. 

### Hooking 

The principle of hooking, when creating a rootkit, is to alter the flow of API calls to use them maliciously.

For Windows, there are various ways to achieve this, but I will focus on one: IAT Hooking. 
The IAT (Import Address Table) contains pointers to:
- DLLs
- function names and addresses for those DLLs

There are PE (Portable Executable) files, such as common DLLs used in Windows (e.g., user32.dll), 
that contain this IAT structure.

### Hiding 

[TODO]

## Steps 

### Hooking 

- Making a function that locate the IAT of user32.dll [done]
- Find the address of the function to hook [done]
- Replace the address [done]
- Write a hook function [done]
- Optional : restoration of the old function address

### Hiding 

[TODO]

