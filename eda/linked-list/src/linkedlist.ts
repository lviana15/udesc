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

function append(List: LList, value: number) {
    const newNode = createNode(value)
    List.tail = newNode
}

