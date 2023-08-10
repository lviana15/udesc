
type LNode = {
    data: number;
    next: LNode | null;
}

type LList = {
    head: LNode;
    tail: LNode | null;
}

function createNode(value: number): LNode {
    return {
        data: value,
        next: null,
    }
}

function createList(value: number): LList {
    const head: LNode = createNode(value)
    const tail = null

    return { head, tail }
}

function insert(List: LList, value: number) {
    const newNode = createNode(value)
    newNode.next = List.head
    List.head = newNode
}

function append(List: LList, value: number) {
    const newNode = createNode(value)
    if (List.tail != null)
        List.tail.next = newNode
}

function lengthList(List: LList): number {
    let length = 0;
    let node = List.head

    while (node.next != null) {
        length++
        node = node.next
    }
    return length;
}

function printList(List: LList): void {
    let node = List.head

    while (node.next != null) {
        console.log(`[${node.data}] `)
        node = node.next
    }
}

let myList = createList(1)
insert(myList, 10)
insert(myList, 23)
insert(myList, 6)
printList(myList)
console.log(lengthList(myList))

