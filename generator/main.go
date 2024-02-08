package main

import (
	"fmt"
	"math/rand"
	"os"
	"time"
)

// baseSentences provides a set of sentences to construct lorem ipsum text.
var baseSentences = []string{
	"Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
	"Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.",
	"Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.",
	"Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.",
	"Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.",
	"Praesent sapien massa, convallis a pellentesque nec, egestas non nisi.",
	"Curabitur arcu erat, accumsan id imperdiet et, porttitor at sem.",
	"Vivamus magna justo, lacinia eget consectetur sed, convallis at tellus.",
	"Mauris blandit aliquet elit, eget tincidunt nibh pulvinar a.",
	"Vestibulum ac diam sit amet quam vehicula elementum sed sit amet dui.",
}

func generateParagraph(minSentences, maxSentences int) string {
	var paragraph string
	numSentences := rand.Intn(maxSentences-minSentences+1) + minSentences
	for i := 0; i < numSentences; i++ {
		sentence := baseSentences[rand.Intn(len(baseSentences))]
		paragraph += sentence + " "
	}
	return paragraph
}

func main() {
	// Initialize random seed
	rand.Seed(time.Now().UnixNano())

	// TargetSize 16 MB
	const targetSize = 16 * 1024 * 1024
	filename := "large_formatted_lorem_ipsum.txt"

	// Create file
	file, err := os.Create(filename)
	if err != nil {
		fmt.Printf("Error creating file: %v\n", err)
		return
	}
	defer file.Close()

	var fileSize int64
	for fileSize < targetSize {
		paragraph := generateParagraph(5, 10) // Generate paragraphs with 5 to 10 sentences
		paragraph += "\n\n"                   // Add two newline characters for paragraph spacing
		n, err := file.WriteString(paragraph)
		if err != nil {
			fmt.Printf("Error writing to file: %v\n", err)
			return
		}
		fileSize += int64(n)
	}

	fmt.Println("Large text file generated successfully.")
}
