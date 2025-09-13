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
    }
  }
}


