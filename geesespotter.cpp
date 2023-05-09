#include <iostream>
#include "geesespotter_lib.h"


char *createBoard(std::size_t xdim, std::size_t ydim){
    std::size_t capacity{xdim * ydim};
    char *board{new char[capacity]{}};
    return board;
}

void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){
    int count{0};
    std::size_t capacity{xdim * ydim};
    for(int k{0}; k < capacity; ++k){
        if(board[k] != 0x09){
            if(k % xdim == 0){ //Left Edge
                if(board[k+1] == 0x09){ //Right
                    count++;
                }
                if((board[k-xdim] == 0x09) && (k-xdim < capacity)) { //Top
                    count++;
                }
                if((board[k+xdim] == 0x09) && (k+xdim < capacity)){ //Bottom
                    count++;
                }
                if((board[k+xdim+1] == 0x09) && (k+xdim+1 < capacity)){ //Bottom Right Diagonal
                    count++;
                }
                if((board[k-xdim+1] == 0x09) && (k-xdim+1 < capacity)){ //Top Right Diagonal
                    count++;
                }
            }else if(k % xdim  == xdim -1){//Right Edge
                if(board[k-1] == 0x09){ //Left
                    count++;
                }
                if((board[k-xdim] == 0x09) && (k-xdim < capacity)){ //Top
                    count++;
                }
                if((board[k+xdim] == 0x09) && (k+xdim < capacity)){ //Bottom
                    count++;
                }
                if((board[k+xdim-1] == 0x09) && (k+xdim-1 < capacity)){ //Bottom Left Diagonal
                    count++;
                }
                if((board[k-xdim-1] == 0x09) && (k-xdim-1 < capacity)){ //Top Left Diagonal
                    count++;
                }
            }else{
                if(board[k+1] == 0x09){ //Right
                    count++;
                }
                if(board[k-1] == 0x09){ //Left
                    count++;
                }
                if((board[k-xdim] == 0x09) && (k-xdim < capacity)) { //Top
                    count++;
                }
                if((board[k+xdim] == 0x09) && (k+xdim < capacity)){ //Bottom
                    count++;
                }
                if((board[k+xdim+1] == 0x09) && (k+xdim+1 < capacity)){ //Bottom Right Diagonal
                    count++;
                }
                if((board[k-xdim+1] == 0x09) && (k-xdim+1 < capacity)){ //Top Right Diagonal
                    count++;
                }
                if((board[k+xdim-1] == 0x09) && (k+xdim-1 < capacity)){ //Bottom Left Diagonal
                    count++;
                }
                if((board[k-xdim-1] == 0x09) && (k-xdim-1 < capacity)){ //Top Left Diagonal
                    count++;
                }
            }
            
            board[k] = count;
        }
        count = 0;
    }
}


void hideBoard(char * board, std::size_t xdim, std::size_t ydim){
    std::size_t capacity{xdim * ydim};
    for (int k{0}; k < capacity; k++){
        board[k] |= hiddenBit();
    }
}

void cleanBoard(char * board){
    delete[] board;
    board = nullptr;
}

void printBoard(char * board, std::size_t xdim, std::size_t ydim){
    for (int k{0}; k < ydim; k++){
        for (int i{0}; i < xdim; i++){
            if((board[i + (xdim * k)] >= 0x20) && (board[i + (xdim * k)] <= 0x29)){
                std::cout<< "*";
            }else if((board[i + (xdim * k)] >= 0x30) && (board[i + (xdim * k)] <= 0x39)){
                std::cout<< "M";
            }else if(board[i + (xdim * k)] == 0x00){
                std::cout<< "0";
            }else if(board[i + (xdim * k)] == 0x01){
                std::cout<< "1";
            }else if(board[i + (xdim * k)] == 0x02){
                std::cout<< "2";
            }else if(board[i + (xdim * k)] == 0x03){
                std::cout<< "3";
            }else if(board[i + (xdim * k)] == 0x04){
                std::cout<< "4";
            }else if(board[i + (xdim * k)] == 0x05){
                std::cout<< "5";
            }else if(board[i + (xdim * k)] == 0x06){
                std::cout<< "6";
            }else if(board[i + (xdim * k)] == 0x07){
                std::cout<< "7";
            }else if(board[i + (xdim * k)] == 0x08){
                std::cout<< "8";
            }else if(board[i + (xdim * k)] == 0x09){
                std::cout<< "9";
            }
        }
        std::cout<<std::endl;
    }
}

int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    std::size_t capacity{xdim * ydim};

    if((board[yloc * xdim + xloc] >= 0x30) && (board[yloc * xdim + xloc] <= 0x39)){
        return 1;
    }else if((board[yloc * xdim + xloc] >= 0x00) && (board[yloc * xdim + xloc] <= 0x08)){
        return 2;
    }else if((board[yloc * xdim + xloc] == 0x09) || (board[yloc * xdim + xloc] == 0x29)){
        board[yloc * xdim + xloc] ^= hiddenBit();
        return 9;
    }else if((board[yloc * xdim + xloc] >= 0x20) && (board[yloc * xdim + xloc] <= 0x28)){
        if(board[yloc * xdim + xloc] == 0x20){
            if(yloc * xdim + xloc % xdim == 0){ //Left Edge
                if((board[yloc * xdim + xloc+1] != 0x29) || (board[yloc * xdim + xloc+1] != 0x39)){ //Right
                    board[yloc * xdim + xloc + 1] ^= hiddenBit();
                }
                if(((board[yloc * xdim + xloc-xdim] != 0x29) || (board[yloc * xdim + xloc-xdim] != 0x39)) && (yloc * xdim + xloc-xdim < capacity)) { //Top
                    board[yloc * xdim + xloc - xdim] ^= hiddenBit();
                }
                if(((board[yloc * xdim + xloc+xdim] != 0x29) || (board[yloc * xdim + xloc+xdim] != 0x39)) && (yloc * xdim + xloc+xdim < capacity)){ //Bottom
                    board[yloc * xdim + xloc +xdim] ^= hiddenBit();
                }
                if(((board[yloc * xdim + xloc+xdim+1] != 0x29) || (board[yloc * xdim + xloc+xdim+1] != 0x39)) && (yloc * xdim + xloc+xdim+1 < capacity)){ //Bottom Right Diagonal
                    board[yloc * xdim + xloc + xdim +1] ^= hiddenBit();
                }
                if(((board[yloc * xdim + xloc-xdim+1] != 0x29) || (board[yloc * xdim + xloc-xdim+1] != 0x39)) && (yloc * xdim + xloc-xdim+1 < capacity)){ //Top Right Diagonal
                    board[yloc * xdim + xloc - xdim +1] ^= hiddenBit();
                }
            }else if(yloc * xdim + xloc % xdim  == xdim -1){//Right Edge
                if((board[yloc * xdim + xloc-1] != 0x29) || (board[yloc * xdim + xloc-1] != 0x39)){ //Left
                    board[yloc * xdim + xloc -1] ^= hiddenBit();
                }
                if(((board[yloc * xdim + xloc-xdim] != 0x29) || (board[yloc * xdim + xloc-xdim] != 0x39)) && (yloc * xdim + xloc-xdim < capacity)){ //Top
                    board[yloc * xdim + xloc - xdim] ^= hiddenBit();
                }
                if(((board[yloc * xdim + xloc+xdim] != 0x29) || (board[yloc * xdim + xloc+xdim] != 0x39)) && (yloc * xdim + xloc+xdim < capacity)){ //Bottom
                    board[yloc * xdim + xloc + xdim] ^= hiddenBit();
                }
                if(((board[yloc * xdim + xloc+xdim-1] != 0x29) || (board[yloc * xdim + xloc+xdim-1] != 0x39)) && (yloc * xdim + xloc+xdim-1 < capacity)){ //Bottom Left Diagonal
                    board[yloc * xdim + xloc + xdim] ^= hiddenBit();
                }
                if(((board[yloc * xdim + xloc-xdim-1] != 0x29) || (board[yloc * xdim + xloc-xdim-1] != 0x39)) && (yloc * xdim + xloc-xdim-1 < capacity)){ //Top Left Diagonal
                    board[yloc * xdim + xloc -xdim -1] ^= hiddenBit();
                }
            }else{
                if((board[yloc * xdim + xloc-1] != 0x29) || (board[yloc * xdim + xloc-1] != 0x39)){ //Left
                    board[yloc * xdim + xloc -1] ^= hiddenBit();
                }
                if(((board[yloc * xdim + xloc-xdim] != 0x29) || (board[yloc * xdim + xloc-xdim] != 0x39)) && (yloc * xdim + xloc-xdim < capacity)){ //Top
                    board[yloc * xdim + xloc -xdim] ^= hiddenBit();
                }
                if(((board[yloc * xdim + xloc+xdim] != 0x29) || (board[yloc * xdim + xloc+xdim] != 0x39)) && (yloc * xdim + xloc+xdim < capacity)){ //Bottom
                    board[yloc * xdim + xloc + xdim] ^= hiddenBit();
                }
                if(((board[yloc * xdim + xloc+xdim-1] != 0x29) || (board[yloc * xdim + xloc+xdim-1] != 0x39)) && (yloc * xdim + xloc+xdim-1 < capacity)){ //Bottom Left Diagonal
                    board[yloc * xdim + xloc +xdim - 1] ^= hiddenBit();
                }
                if(((board[yloc * xdim + xloc-xdim-1] != 0x29) || (board[yloc * xdim + xloc-xdim-1] != 0x39)) && (yloc * xdim + xloc-xdim-1 < capacity)){ //Top Left Diagonal
                    board[yloc * xdim + xloc - xdim -1] ^= hiddenBit();
                }
                if(((board[yloc * xdim + xloc+xdim+1] != 0x29) || (board[yloc * xdim + xloc+xdim+1] != 0x39)) && (yloc * xdim + xloc+xdim+1 < capacity)){ //Bottom Right Diagonal
                    board[yloc * xdim + xloc + xdim + 1] ^= hiddenBit();
                }
                if(((board[yloc * xdim + xloc-xdim+1] != 0x29) || (board[yloc * xdim + xloc-xdim+1] != 0x39)) && (yloc * xdim + xloc-xdim+1 < capacity)){ //Top Right Diagonal
                    board[yloc * xdim + xloc - xdim +1] ^= hiddenBit();
                }
                if((board[yloc * xdim + xloc+1] != 0x29) || (board[yloc * xdim + xloc+1] != 0x39)){ //Right
                    board[yloc * xdim + xloc +1] ^= hiddenBit();
                }
            }
        }//of its a zero
        board[yloc * xdim + xloc] ^= hiddenBit();     
        return 0;
    }
    return 0;
}

int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
    board[yloc * xdim + xloc] ^= markedBit();
    return 0;
}

bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
    bool all_geese {true};
    std::size_t capacity{xdim * ydim};

    for (int k{0}; k < capacity; k++){
        if(board[k] != 0x29){
            all_geese = false;
        }
    }

    if(all_geese){
        return false;
    }

    
    for (int k{0}; k < capacity; k++){
        if (board[k] >= 0x20 && (board[k] != 0x29 && board[k] != 0x39)){
            return false;
        }       
    }
    
   

    return true;
}
