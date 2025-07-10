class ToDo {
    constructor(description) {
        this.description = description
        this.completed = false
    }

    toggleCompletion() {
        this.completed = !this.completed
    }
}

class Model {
    constructor() {
        this.todos = []
    }

    addTodo(description) {
        const newTodo = new ToDo(description)
        this.todos.push(newTodo)
    }

    removeTodo(index) {
        this.todos.splice(index, 1)
    }

    getTodos() {
        return this.todos
    }
}

class Controller {
    constructor(model) {
        this.model = model
        this.todoInput = document.getElementById('todoInput')
        this.addTaskButton = document.getElementById('addTaskButton')
        this.todoList = document.getElementById('todoList')

        this.addTaskButton.addEventListener('click', () => this.addTask())

        this.renderTodos()
    }

    addTask() {
        const taskDescription = this.todoInput.value.trim()
        if (taskDescription) {
            this.model.addTodo(taskDescription)
            this.todoInput.value = ''
            this.renderTodos()
        }
    }

    removeTask(index) {
        this.model.removeTodo(index)
        this.renderTodos
    }

    renderTodos() {
        this.todoList.innerHTML = ''

        const todos = this.model.getTodos()

        todos.forEach((todo, index) => {
            const li = document.createElement('li')

            const taskText = document.createTextNode(todo.description)

            if (todo.completed) {
                li.classList.add('completed')
            }

            li.appendChild(taskText)

            const checkbox = document.createElement('input')
            checkbox.type = 'checkbox'
            checkbox.checked = todo.completed
            checkbox.addEventListener('click', () => {
                todo.toggleCompletion()
                this.renderTodos()
            })

            const deleteButton = document.createElement('button')
            deleteButton.textContent = 'Delete'
            deleteButton.addEventListener('click', () => this.removeTask(index))

            li.appendChild(checkbox)
            li.appendChild(deleteButton)
            this.todoList.appendChild(li)
        })
    }
}

const todoModel = new Model()
const todoController = new Controller(todoModel)
