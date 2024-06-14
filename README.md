<h2>PSkrypt - simple programming language</h2>
Simple programming language that has while loops(also nested), variable declarations(only integer ones), if statements and arithmetic operations. 
<h4>Requirements and support</h4>
Running this language is only supported for linux, and requires CMake, NASM and LD
<h3>Running the language:</h3>

```
1. git clone https://github.com/JabloZ/pskrypt_lang
2. create directory build in pskrypt_lang (mkdir build)
3. cmake -s . -b build
4. cmake --build build
5. ./{pskrypt-executable-file} {filename.ps} (without brackets)
```

Example:<br>
./build/pskrypt_lang example.ps<br>
./output<br>
echo $? //should return 88 for example file
<br>
<br>
<h3>Language keywords:</h3>
<br>

var - declares variable, also used to change variable value
  sample usage: 
  <br>
  
  ```
  var b=2;   
  var b=b+2+6+1;
  ```
<h4>while</h4>
  used to create while loops, comes with instructions: "greater","greater_equal","lesser","lesser_equal", "equal", "not equal", "end_loop".
  needs to be closed with end_loop statement
  
  sample usage: 
  <br>
   ```
  var c=10;
  var d=0;
  while c greater 0;
    var d=d+2;
    var c=c-1;
  end_loop;
  return d;
   ```
<h4>if</h4>
  used to create if statements, comes with instructions: "greater","greater_equal","lesser","lesser_equal","equal", "not equal", "end_if".
  needs to be closed with end_if statement
  sample usage: 
  <br>
  
  ```
  var c=10;
  if c greater 5;
  return 20; //returns 20
  end_if;
  return c; // doesnt return the c
  ```
<h4>return</h4>
  returns value from the program (as exit)
  sample usage: 
  <br>
  
  ```
  return 2; //returns 2
  ```

<h4>example</h4>
Example program combining all of these above: maximum consecutive fibonacci numbers sum lower than a 100
<br>

```
var fiba=0;
var fibb=1;
var sum=1;
var nth=0;
while sum lesser_equal 100;
    var nth=fiba+fibb;
    fiba=fibb;
    fibb=nth;        
    var if_sum_higher=sum+nth;
    if if_sum_higher greater 100;
        return sum;
    end_if;
    sum=sum+nth;
end_loop;

return sum; // returns 88 (0+1+1+2+3+5+8+13+21+34)
```
