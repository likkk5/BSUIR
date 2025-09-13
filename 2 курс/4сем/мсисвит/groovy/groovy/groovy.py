def matrix = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9]
]

for (rowIndex in 0..<matrix.size()) {
  println("Row $rowIndex:")
  for (colIndex in 0..<matrix[rowIndex].size()) {
    def element = matrix[rowIndex][colIndex]
    println("Element [$rowIndex][$colIndex]: $element")

    switch (element) {
      case 1:
        println("This is number one")
        if (element % 2 == 0) {
          println("This is an even number")
        } else {
          println("This is an odd number")
        }
        break
      case 2:
        println("This is number two")
        if (element % 2 == 0) {
          println("This is an even number")
        } else {
          println("This is an odd number")
        }
        break
      case 3:
        println("This is number three")
        if (element % 2 == 0) {
          println("This is an even number")
        } else {
          println("This is an odd number")
          if (element % 3 == 0) {
            println("This number is divisible by 3")
            if (element % 5 == 0) {
              println("This number is divisible by 5")
            } else {
              println("This number is not divisible by 5")
            }
          } else {
            println("This number is not divisible by 3")
          }
        }
        break
      case 4:
        println("This is number four")
        if (element % 2 == 0) {
          println("This is an even number")
        } else {
          println("This is an odd number")
        }
        break
      case 5:
        println("This is number five")
        if (element % 2 == 0) {
          println("This is an even number")
        } else {
          println("This is an odd number")
          if (element % 3 == 0) {
            println("This number is divisible by 3")
            if (element % 5 == 0) {
              println("This number is divisible by 5")
            } else {
              println("This number is not divisible by 5")
            }
          } else {
            println("This number is not divisible by 3")
          }
        }
        break
      case 6:
        println("This is number six")
        if (element % 2 == 0) {
          println("This is an even number")
          if (element % 3 == 0) {
            println("This number is divisible by 3")
            if (element % 5 == 0) {
              println("This number is divisible by 5")
            } else {
              println("This number is not divisible by 5")
            }
          } else {
            println("This number is not divisible by 3")
          }
        } else {
          println("This is an odd number")
        }
        break
      case 7:
        println("This is number seven")
        if (element % 2 == 0) {
          println("This is an even number")
        } else {
          println("This is an odd number")
        }
        break
      case 8:
        println("This is number eight")
        if (element % 2 == 0) {
          println("This is an even number")
          if (element % 4 == 0) {
            println("This number is divisible by 4")
            if (element % 8 == 0) {
              println("This number is divisible by 8")
            } else {
              println("This number is not divisible by 8")
            }
          } else {
            println("This number is not divisible by 4")
          }
        } else {
          println("This is an odd number")
        }
        break
      case 9:
        println("This is number nine")
        if (element % 2 == 0) {
          println("This is an even number")
        } else {
          println("This is an odd number")
          if (element % 3 == 0) {
            println("This number is divisible by 3")
            if (element % 9 == 0) {
              println("This number is divisible by 9")
              if (element < 10 ){
                println("This number less than 10")
                if (element > 5){
                  println("This number greater than 5")
                }
                else {
                  println("This number less than 5")
                }
              }
              else {
                println("This number greater than 10")
              }
            } else {
              println("This number is not divisible by 9")
            }
          } else {
            println("This number is not divisible by 3")
          }
        }
        break
    }
  }
}