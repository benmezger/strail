# strail
A Kernel with suport to the RISC-V ISA

# Introduction

I wrote a small kernel for my bachelor thesis with support to the RISC-V ISA, focussing 
at the education of operating systems, where students and professors may dive into a 
simpler kernel implementation for academic puposes, instead of relying on large kernel code-base.
We hope this project might give students and professors a big picture of the implementation of 
an operating systems and how components communicate with each other.

Although I only had 1 year to write and develop my thesis, it was enough time for 
me to write a small and basic kernel with RISC-V's {machine, supervisor, user}-mode 
support, trap handlers and a basic round-robin scheduling algorithm.
I was approved upon the presentation of my thesis, but I decided to refactor 
the code and allow multiple architecture support, better code organization, a kernel 
interface for communicating with the lower level architectural code and better trap 
handlers and smoother POSIX support.

# Supported ISA's

- [X] RISCV 

# Instruction Set Architecture (ISA)
## RISC-V
  - Enter `main` through `_start`
  - `DIRECT MODE` access to trap handlers
  - Enter machine-mode
