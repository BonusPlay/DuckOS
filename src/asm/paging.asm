[bits 32]

; Intel SDM Table 4-17. Format of a Page-Directory-Pointer-Table Entry (PDPTE) that References a Page Directory
PAGE_EXISTS equ 1 << 0
PAGE_RW     equ 1 << 1

align 0x1000
pml4t:
times (512) dq 0x00

align 0x1000
pml3t:
times (512) dq 0x00

align 0x1000
pml2t:
times (512) dq 0x00

align 0x1000
pml1t:
times (512) dq 0x00

section .text
global _setup_paging:function (_setup_paging.end - _setup_paging)
_setup_paging:
    ; setup pml[2-4]t
    mov dword [pml4t], pml3t + (PAGE_EXISTS | PAGE_RW)
    mov dword [pml3t], pml2t + (PAGE_EXISTS | PAGE_RW)
    mov dword [pml2t], pml1t + (PAGE_EXISTS | PAGE_RW)

    ; loop counter
    mov ecx, 512
    ; addr of current pml1t
    mov edi, pml1t
    ; phys mem addr
    mov edx, (PAGE_EXISTS | PAGE_RW)

    ; setup pml1t
.set_entry:
    mov dword [edi], edx
    add edi, 0x8
    add edx, 0x1000
    loop _setup_paging.set_entry

    mov eax, pml4t
    mov cr3, eax

    ; enable Physical Address Extension
    mov eax, cr4
    or eax, (1 << 5)
    mov cr4, eax

    ; enable Long Mode Enable
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; enable Paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ret
.end
