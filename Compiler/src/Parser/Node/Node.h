#pragma once

class Node 
{
    
};

class ConstructNode : public Node
{

};

class ConstantNode : public Node
{

};

/*
AST for 8 * 9 + 3 / 3 + 2 * 6
programnode
    constructnode add  
        constructnode add 
            constructnode mul 
                constantnode 8 
                constantnode 9 
            constructnode div
                constantnode 3
                constantnode 3
        constructnode mul
            constantnode 2
            constantnode 6  
    
        


assembly 
mov rax, 8 
mul rax, 9
mov rbx 3
div rbx, 3
add rax, rbx
push rax
mov rax, 6
mul rax, 2
pop rbx
add rax, rbx
print rax
*/