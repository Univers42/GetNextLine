#!/bin/bash

clear


draw_ball_2() {

 local x_2=$1
 local y_2=$2

 local prev_x_2=$3
 local prev_y_2=$4

    tput cup $((prev_y_2)) $prev_x_2
    echo "      "
    
    tput cup $((prev_y_2 + 1)) $prev_x_2
    echo "      "

    tput cup $((prev_y_2 + 2)) $((prev_x_2 + 1))
    echo "      "

    
    #draw_grid  "."
    tput cup $y_2 $x_2
    ansi --blue " ### "

    tput cup $((y_2 + 1)) $x_2
    ansi --blue "#####"

    tput cup $((y_2 + 2)) $((x_2 + 1))
    ansi --blue "###"
    
}

ball_collision() {
                if (( x >= lines - 4|| x <= 0 )); then
                  dx=$((dx * -1))
                fi

                if (( y >= cols - 6|| y <= 0 )); then
                  dy=$((dy * -1))
                fi


                if (( x_2 >= lines - 5 || x_2 <= 0 )); then
                  dx_2=$((dx_2 * -1))
                fi

                if (( y_2 >= cols - 6 || y_2 <= 0 )); then
                  dy_2=$((dy_2 * -1))
                fi

                if (( x_3 >= lines - 5 || x_3 <= 0 )); then
                  dx_3=$((dx_3 * -1))
                fi

                if (( y_3 >= cols - 6 || y_3 <= 0 )); then
                  dy_3=$((dy_3 * -1))
                fi

}

draw_ball_3() {
        
  local x_3=$1
  local y_3=$2

  local prev_x_3=$3
  local prev_y_3=$4

    tput cup $((prev_y_3)) $((prev_x_3))
    echo "      "
    
    tput cup $((prev_y_3 + 1)) $((prev_x_3))
    echo "      "

    tput cup $((prev_y_3 + 2)) $((prev_x_3 + 1))
    echo "      "

  tput cup $y_3 $x_3
  ansi --yellow " ### "

  tput cup $((y_3 + 1)) $((x_3))
  ansi --yellow "#####"

  tput cup $((y_3 + 2)) $((x_3 + 1))
  ansi --yellow "###"

  


}


draw_ball() {
 local x=$1
 local y=$2

 local prev_x=$3
 local prev_y=$4

    tput cup $((prev_y)) $((prev_x))
    echo "      "
    
    tput cup $((prev_y + 1)) $((prev_x))
    echo "      "

    tput cup $((prev_y + 2)) $((prev_x + 1))
    echo "      "

    
    tput cup $y $x
    ansi --red " ### "

    tput cup $((y + 1)) $((x))
    ansi --red "#####"

    tput cup $((y + 2)) $((x +1))
    ansi --red "###"


}

draw_grid() {
      local symbol=$1

      for (( j=0;j<$lines; j++ )); do
        for (( i=0;i<$cols; i++  )); do
          if [ $i == $cols ]; then
                echo -n "$symbol"
          else
            echo -n "$symbol"
          fi
        done
      done

}


main() {
        cols=$(tput cols)
        lines=$(tput lines)

        x=$(( 1 + RANDOM % lines / 2 ))
        y=$(( 1 + RANDOM % cols / 2  ))

        x_2=0
        y_2=40

        x_3=$(( lines / 2 ))
        y_3=$(( cols / 2 ))

        dx=1
        dy=1

        dy_2=1
        dx_2=1

        dy_3=1
        dx_3=1

        prev_x=$x
        prev_y=$y

        prev_x_2=$x_2
        prev_y_2=$y_2

        prev_x_3=$x_3
        prev_y_3=$y_3




        while true; do
                draw_ball $y $x $prev_y $prev_x
                draw_ball_2 $y_2 $x_2 $prev_y_2 $prev_x_2
                draw_ball_3 $y_3 $x_3 $prev_y_3 $prev_x_3
                tput civis

                prev_x=$x
                prev_y=$y

                prev_x_2=$x_2
                prev_y_2=$y_2

                prev_x_3=$x_3
                prev_y_3=$y_3

                x=$((x + dx ))
                y=$((y + dy ))

                x_2=$((x_2 + dx_2 ))
                y_2=$((y_2 + dy_2 ))

                x_3=$((x_3 + dx_3))
                y_3=$((y_3 + dy_3))
                

                
                ball_collision






        done
        tput cnorm

}
main