inventory = {}

def add(name, price, amount):
    sell_times = 0
    if price < 0 or amount < 0:
        return
    if name not in inventory:
        inventory[name] = (price, amount, sell_times)


def change(name, amount, sell_times):
    if name in inventory:
        inventory[name] = (inventory[name][0], inventory[name][1] + amount, sell_times)


def ship(line):
    items = line.split("--")
    for product in items:
        order = product.split(",")
        name = "".join(order[0]).strip()
        amount = float("".join(order[1]).strip())
        if name not in inventory or inventory[name][1] - amount < 0 or amount < 0:
            pass
        else:
            change(name, -amount, inventory[name][2] + amount)


def update_inventory(file_name):
    file = open(file_name, 'r')
    for line in file:
        line_split = line.split(' ')
        if line_split[0] == 'add':
            add(line_split[2], float(line_split[3]), float(line_split[4]))
        if line_split[0] == 'change' and (line_split[2] in inventory):
            change(line_split[2], float(line_split[3]), inventory[line_split[2]][2])
        if line_split[0] == 'ship':
            ship(line[11:])

    file.close()


def find_best_selling_product(file_name):
    update_inventory(file_name)
    if not inventory:
        return "", 0
    sell_list = ([(val[2]*val[0], key) for key, val in inventory.items()])
    sell_list.sort(key=lambda x: (-x[0], x[1]))
    inventory.clear()
    return sell_list[0][1], sell_list[0][0]


def find_k_most_expensive_products(file_name, k):
    update_inventory(file_name)
    if not inventory:
        return []
    inventory_list = [[name, details[0]] for name, details in inventory.items()]
    inventory_list.sort(key=lambda x: (-x[1], x[0]))
    inventory_list = [name[0] for name in inventory_list]
    inventory.clear()
    return inventory_list[:k]
