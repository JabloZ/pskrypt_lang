<h2>Project - simple programming language</h2>
Simple programming language that has while loops(also nested), variable declarations(only integer ones), if statements and arithmetic operations. 
<h3>Language keywords:</h3>
<br>
<br>
var - declares variable, also used to change variable value
  sample usage: var b=2;   var b=b+2+6+1;

<br>
<br>
<h4>while</h4>
  used to create while loops, comes with instructions: "greater","greater_equal","lesser","lesser_equal", "equal", "not equal", "end_loop".
  needs to be closed with end_loop statement
  
  sample usage: 
  <br>
  var c=10;<br>
  var d=0;<br>
  while c greater 0;<br>
    var d=d+2;<br>
    var c=c-1;<br>
  end_loop;<br>
  return d;<br>
<br>
<br>

<h4>if</h4>
  used to create if statements, comes with instructions: "greater","greater_equal","lesser","lesser_equal","equal", "not equal", "end_if".
  needs to be closed with end_if statement
  sample usage: 
  <br>
  var c=10;<br>
  if c greater 5;<br>
  return 20; //returns 20<br>
  end_if;<br>
  return c; // doesnt return the c<br>
<br>
<br>
<h4>return</h4>
  returns value from the program (as exit)
  sample usage: 
  <br>
  return 2; //returns 2<br>

<br>
<br>
<h4>example</h4>
Example program combining all of these above: maximum consecutive fibonacci numbers sum lower than a 100
<br>
var fiba=0;<br>
var fibb=1;<br>
var sum=1;<br>
var nth=0;<br>

while sum lesser_equal 100;<br>
    var nth=fiba+fibb;<br>
    fiba=fibb;<br>
    fibb=nth;        <br>
    var if_sum_higher=sum+nth;<br>
    if if_sum_higher greater 100;<br>
        return sum;<br>
    end_if;<br>
    sum=sum+nth;<br>
end_loop;<br>

return sum;<br>
