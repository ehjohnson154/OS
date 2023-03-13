




// Find_Space(bytes):

//     bytes = bytes + GET_PADDING(bytes)

//     walk the linked list looking for a space at least "bytes" big

//         if current space big enough:

//             # vvv splitting code vvv

//             if the space is big enough to split:
//                 Split_Space(current, size) into current and new

//             # ^^^ splitting code ^^^

//             Mark current space in use
//             Return pointer to current space
        
//     return NULL since we're out of memory



// Split_Space(current_node, requested_size):
//     If current_node big enough to split:
//         Add a new struct block with the remaining unused space
//         Wire it into the linked list


void split_space(current node, requested_size){


}