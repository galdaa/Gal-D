#!/bin/sh
read -p "Enter massage: " massage

push() {
    git add ~/git/
    git commit -m "$massage"
    git push -u origin master 
    #gal.dahan 305213936
    echo "push by $massage"
}

push "$massage"


