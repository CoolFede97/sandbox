local Enemy = {}

function Enemy:new()
    local obj =
    {
        health = 100,
        speed = 50,
    }

    self.__index = self
    setmetatable(obj, self)

    return obj
end

function Enemy:TakeDamage(damage)
    self.health = self.health - damage
end

local Zombie = setmetatable({}, Enemy)
Zombie.__index = Zombie

function Zombie:new()
    local obj = Enemy:new(self)

    obj.brainsEaten = 0

    setmetatable(obj, self)

    return obj
end

function Zombie:EatBrain()
    self.brainsEaten = self.brainsEaten + 1
end

local zombie1 = Zombie:new()

print(zombie1.health)

zombie1:TakeDamage(20)

print(zombie1.health)
