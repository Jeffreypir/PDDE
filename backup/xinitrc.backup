#!/bin/bash
#exec i3
#exec dwm
xrdb ~/.Xresources  

setxkbmap -option caps:none
xmodmap -e 'keycode 135 = slash question'  
#feh --bg-fill /home/jefferson/Downloads/712781.jpg 
feh --bg-fill /home/jefferson/Downloads/428976.png  
xmodmap -e "keycode 66 = colon"
exec  /home/jefferson/Documentos/janelas/dwm-6.1/dwm 
echo 10  > /sys/class/backlight/radeon_bl0/brightness 

