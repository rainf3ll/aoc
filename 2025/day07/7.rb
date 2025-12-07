# frozen_string_literal: true

def solve1(data, result = 0)
  x = [data[0].index('S')]
  data.each do |line|
    x.dup.each do |coord|
      next if line[coord] != '^'

      result += 1
      (x << coord - 1 << coord + 1).delete(coord)
      x.uniq!
    end
  end
  result
end

def solve2(data, dp_arr = Array.new(data.size) { Array.new(data[0].size, 0) })
  dp_arr[0][data[0].index('S')] = 1
  (1...dp_arr.size).each do |y|
    (0...dp_arr[y].size).each do |x|
      dp_arr[y][x] += dp_arr[y - 1][x]
      next if data[y][x] != '^'

      dp_arr[y][x - 1] += dp_arr[y][x] if x.positive?
      dp_arr[y][x + 1] += dp_arr[y][x] if x < dp_arr[y].size - 1
      dp_arr[y][x] = 0
    end
  end
  dp_arr[-1].sum
end

data = File.readlines('bigboy.txt').map { |line| line.chomp.chars }
puts "silver: #{solve1(data)}"
puts "gold: #{solve2(data)}"
