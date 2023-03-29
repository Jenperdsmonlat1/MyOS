; Fonction permettant de déplacer le curseur.
; Prends en paramètre:
;   Les données à envoyer
;   Le port sur lequel envoyer ces données
; Puisque tous les arguments passés à la fonction sont
; placés sur la pile, on utile le registre esp.

GLOBAL outb
GLOBAL inb

outb:

    mov al, [esp+8]
    mov dx, [esp+4]
    out dx, al
    ret

inb:

    mov dx, [esp+4]
    in al, dx
    ret