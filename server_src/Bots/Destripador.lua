WALKABLE = 0
DIVISIONS_AMOUNT = 10
PI = 3.1415926
BIG_DISTANCE = 10000
KNIFE_RANGE = 0.5

NOT_MOVE = 0
MOVE_FORWARDS = 1
MOVE_BACKWARDS = 2
TURN_LEFT = 3
TURN_RIGHT = 4
ATTACK = 5

function getBotInstruction(map, positions, posX, posY, dirX, dirY)

    nearestPlayerX = BIG_DISTANCE
    nearestPlayerY = BIG_DISTANCE

    numberOfPlayers = tableLength(positions)/2

    --[ Obtengo la posicion del jugador visible mas cercano ]--
    for i = 0, numberOfPlayers - 1 do
            playerX = positions[2 * i]
            playerY = positions[2 * i + 1]
        if isInTheFieldOfView(posX, playerX, posY, playerY, map) == true then
            if math.sqrt((posX - playerX)^2 + (posY - playerY)^2) <
            math.sqrt((posX - nearestPlayerX)^2 + (posY - nearestPlayerY)^2) then
                nearestPlayerX = playerX
                nearestPlayerY = playerY
            end
        end
    end

    if nearestPlayerX == BIG_DISTANCE and nearestPlayerY == BIG_DISTANCE then
        return NOT_MOVE
    elseif math.sqrt((nearestPlayerX - posX)^2 + (nearestPlayerY - posY)^2) < KNIFE_RANGE then
        return ATTACK
    elseif angle(posX, nearestPlayerX, dirX, dirY, posY, nearestPlayerY) <= (PI/12) then
        return MOVE_FORWARDS
    else
        return TURN_RIGHT
    end

end

function tableLength(T)
    local count = 0
    for i in pairs(T) do
        count = count + 1
    end
    return count
end

function isInTheFieldOfView(xP1, xP2, yP1, yP2, map)
    inTheFieldOfView = true

    dirX = xP2 - xP1
    dirY = yP2 - yP1
    norm = math.sqrt(dirX * dirX + dirY * dirY)

    stepX = dirX/(norm * DIVISIONS_AMOUNT)  -- Step de norma igual a 1/10
    stepY = dirY/(norm * DIVISIONS_AMOUNT)  -- Step de norma igual a 1/10

    for i = 0, (DIVISIONS_AMOUNT * norm) do
        if map[math.floor(xP1 + i * stepX)][math.floor(yP1 + i * stepY)] ~= WALKABLE then
            inTheFieldOfView = false
            break
        end
    end

    return inTheFieldOfView;
end

function angle(xP1, xP2, dirXP1, dirYP1, yP1, yP2)
    diffX = xP2 - xP1
    diffY = yP2 - yP1
    theta = math.acos((dirXP1 * diffX + dirYP1 * diffY) / math.sqrt(diffX^2 + diffY^2))
    return theta
end