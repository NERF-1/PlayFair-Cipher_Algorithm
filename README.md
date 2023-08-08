# PlayFair Cipher Algorithm.
### A Cipher Algorithm that is used to encrypt PlainText.

# Description:
### The story of this algorithm:
The Playfair cipher is a historical encryption algorithm that was invented in 1854 by Charles Wheatstone, but named after Lord Playfair who promoted its use. It is a manual symmetric encryption technique that encrypts pairs of letters **(digraphs)** instead of single letters, making it harder to break with frequency analysis. It was used by the British and Australian forces in the Second Boer War and World War I and II for tactical purposes, as it was fast and easy to use without special equipment.

### How This Algorithm Works?
### Encryption 🔒
To begin, generate a key square, which is a 5x5 grid of letters. It should consist of the unique letters of the key, followed by the remaining letters of the alphabet in order. Omit one letter, usually J, to fit the 25 letters in the grid.
<br>
### For example, Your 🔑 key square might look like this:

| R | O   | C | K | A |
|---|-----|---|---|---|
| B | D | E | F | G |
| H | I / J | L | M | N |
| P | Q   | S | T | U |
| V | W   | X | Y | Z |

**Next, split your plaintext into pairs of letters (digraphs).<br>**
* If there is an odd number of letters, add a filler letter, usually Z, at the end.<br>
* If there are any repeated letters in a digraph, insert a filler letter between them.<br>
### For example, Your plaintext would be split into: BA SE<br>
**Then**, apply the encryption rules for each digraph according to its positions in the key square.<br>
### The rules are: <br>
* If both letters are in the same column, take the letter below each one (wrapping around to the top if at the bottom).<be>
* If both letters are in the same row, take the letter to the right of each one (wrapping around to the left if at the rightmost position).<br>
* If neither of the above rules is true, form a rectangle with the two letters and take the letters on the opposite corners of the rectangle.<br>
### For example, applying these rules to your plaintext would result in:<br>
**BA -> GR**<br>
**SE -> XL**<br>
<br>
#### Finally, join the encrypted digraphs together to get your ciphertext. <br>
### Your ciphertext would be: "GRXL"

### Decryption 🔓
To decrypt the ciphertext using the Playfair cipher, you need to use the same key square and apply the inverse rules for each digraph.<br>
### The steps are:<br>

**First**, split your ciphertext into pairs of letters (digraphs).<br>
**Next**, apply the inverse rules for each digraph according to its positions in the key square.<br>
### The inverse rules are:
* If both letters are in the same column, take the letter above each one (wrapping around to the bottom if at the top).<br>
* If both letters are in the same row, take the letter to the left of each one (wrapping around to the right if at the leftmost position).<br>
* If neither of the above rules is true, form a rectangle with the two letters and take the letters on the opposite corners of the rectangle.<br>
* Then, join the decrypted digraphs together to get your plaintext.<br>
* Finally, remove any filler letters that were added during encryption.<br>
### For example, applying these steps to your ciphertext would result in:<br>

**GRXL -> GR XL**<br>
**GR -> BA**<br>
**XL -> SE**<br>
**BASE -> BASE**<br>

### And then your plaintext would be: "BASE".

### What you can do with this Algorithm?
You can use this algorithm to encrypt the data between two users or to encrypt your database. This way, even if you get hacked, nobody can understand your data.

## The Project:
### The Structures of the files.
```bash
.
├── ...
├── PlayFair-Cipher_Algorithm                 # The main Folder That Contains our project.
│   ├── cipher              # Compiled File of our `cipher.c`.
│   ├── cipher.c            # This is where our source code has been written.
│   └── README.md           # The explanation folder that you are reading right now 😅.
└── ...
```
I have made an explanation for every single method and line of code inside `cipher.c`.<br>
You can see that I have not distributed `cipher.c` in sub-files because I see that there is no actual need for that! <br>
### What I have used Mainly in my project As concepts were:
* DATA STRUCTURES
* POINTERS AND MEMORY ALLOCATION
* STRUCTS
* NESTED CALLS METHODS <br><br>
These approaches I take to make the code more (readable, and simple)  so it can be understandable for everyone have read this algorithm. You might see that sometimes I am implementing similar code in a different way, This is just For "diversity"  so there is nothing specific.<br>
Another thing to mention is that my code can encrypt and decrypt more than one word, which means you can encrypt and decrypt clauses.<br>
My code can also encrypt and decrypt files, all you need is to add the functionality of reading the files and send the words that you read from files word by word as an argument to the `encrypt(char **word)` method if you want to encrypt and the `decrypt(char **word)` method for decryption, these methods will handle everything and store the encrypted and decrypted words inside the linked list you can after that call `print_list()` method to print the whole words.


### What are the goals of my program?
The goal of my program is to use the Playfair algorithm to encrypt the data while providing a friendly CLI to interact with the users. This program is very useful for students who are studying various algorithms because it shows what the 5x5 matrix looks like and it displays the substitution for every single letter. This makes it easy to track and understand the encryption process. Also, using this program will save their time, because they can see how the key matrix and the cipher text are generated quickly. They can also understand the source code and see how they can apply this algorithm in various programs or applications, such as encrypting databases as I mentioned before.

### Why did I choose this algorithm?
I was curious about securing the data and I was reading about various algorithms. When I saw this algorithm and its story, it sounded really interesting to me and a bit challenging. At the same time, I wanted to improve my skills in C language because I love it and I thought that this algorithm was suitable. Another thing that I love is the things that are related to computer science and complexity, more than the commercial aspects.

### What have I learned while implementing this algorithm?

* I improved my skills in dealing with arrays and iterating over them.<br>
* I gained more practice in using malloc and allocating memory dynamically.<br>
* I became more accurate and had a better understanding of pointers and memory management.<br>
* I improved my understanding of structs and how to benefit from them.<br>
* I enhanced my debugging skills and learned how to fix errors and bugs.<br>
* I understood how to create a friendly CLI program that interacts with the users.<br>
* I developed my logic and learned something new about securing the data and a bit about the history of this algorithm and some others like Caesar and Hill cipher algorithms.<br>


