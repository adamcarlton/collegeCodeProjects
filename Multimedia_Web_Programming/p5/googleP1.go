package solution

// you can also use imports, for example:
// import "fmt"
// import "os"
import "strings"
import "sort"
// you can write to stdout for debugging purposes, e.g.
// fmt.Println("this is a debug message")

func Solution(S string) string {
    if S == "00:00" {
		return S
	}
	splitOnColon := strings.Split(S, ":")
	hours := splitOnColon[0]
	min := splitOnColon[1]
	if min == "00" {
		if hours[0] > hours[1] {
			return min + ":" + string(hours[1]) + string(hours[0])
		}
		return min + ":" + hours
	} else if hours == "00" {
		if min[0] > min[1] {
			return "0" + string(min[1]) + ":" + "0" + string(min[0])
		} else if min[0] == 0 {
			return hours + ":" + string(min[1]) + string(min[0])
		}
		return "0" + string(min[0]) + ":" + "0" + string(min[1])
	} else {
		sortThese := []string{string(hours[0]), string(hours[1]), string(min[0]), string(min[1])}
		sort.Strings(sortThese)
		finalString := ""
		for i := 0; i < len(sortThese); i++ {
			finalString += sortThese[i]
			if i == 1 {
				finalString += ":"
			}
		}
		return finalString
	}
}