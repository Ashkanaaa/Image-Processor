function Init(){

    const container = document.getElementById("radioButtonsContainer");

    // Array of options for the radio buttons
    const options = ["Grayscale", "Spotlight", "Watermark", "Scramble", "Unscramble"];

    // Create and add radio buttons to the container
    options.forEach((option) => {
        const radioButton = document.createElement("input");
        radioButton.type = "radio";
        radioButton.name = "process"; 
        radioButton.value = option;

        const label = document.createElement("label");
        label.textContent = option;
        
        switch(option){
            case "Grayscale":
                radioButton.addEventListener('change', handle_Grayscale)
                break
            case "Spotlight":
                radioButton.addEventListener('change', handle_Spotlight)
                break
            case "Watermark":
                radioButton.addEventListener('change', handle_Watermark)
                break
            case "Scramble":
                radioButton.addEventListener('change', handle_Scramble)
                break
            case "Unscramble":
                radioButton.addEventListener('change', handle_Unscramble)
                break
            default:
                console.log("Could not add the radio button event listner")
        }

        container.appendChild(radioButton);
        container.appendChild(label);
    });
}

//parent div for adding submit form
const parentDiv = document.getElementById("Parent");

function handle_Grayscale(){
    postData('Grayscale')
    upload_form(0)
}

function handle_Spotlight(){
    postData('Spotlight')
    upload_form(1)
}

function handle_Watermark(){
    postData('Watermark')
    upload_form(2)
}

function handle_Scramble(){
    postData('Scramble')
    upload_form(0)
}

function handle_Unscramble(){
    postData('Unscramble')
    upload_form(0)
}

//create the upload form based on the selected process
function upload_form(num){

    //clearing the previous content
    if (parentDiv !== null) {
        parentDiv.innerHTML = "";
    } else {
        console.log("Container div not found.");
    }

    //Spotlight
    if(num == 1){
        //create the form
        const form = document.createElement("form");
        form.action = "/upload";
        form.method = "post";
        form.enctype = "multipart/form-data";

        //create the image input
        const label1 = document.createElement("label");
        label1.textContent = "Upload the photo:";
        const fileInput = document.createElement("input");
        fileInput.type = "file";
        fileInput.id = "image";
        fileInput.name = "image";
        fileInput.accept = "image/*";
        fileInput.required = true;
        fileInput.textContent = "Upload the first Image"
        form.appendChild(label1);
        form.appendChild(fileInput);

        // Create the x coordinate input
        const xCoordinate = document.createElement("input");
        xCoordinate.type = "text";
        xCoordinate.id = "xCoordinate";
        xCoordinate.name = "xCoordinate";
        xCoordinate.required = true;
        xCoordinate.placeholder = "X Coordinate"
        form.appendChild(xCoordinate);

        // Create the y coordinate input
        const yCoordainate = document.createElement("input");
        yCoordainate.type = "text";
        yCoordainate.id = "yCoordinate";
        yCoordainate.name = "yCoordinate";
        yCoordainate.required = true;
        yCoordainate.placeholder = "Y Coordinate"
        form.appendChild(yCoordainate);

        // Create and append the submit button
        const submitInput = document.createElement("input");
        submitInput.type = "submit";
        submitInput.value = "Upload";
        form.appendChild(submitInput);

        // Append the form to the document body or any other desired location
        parentDiv.appendChild(form);

    }else if(num == 2){ // Watermark
        //create the form
        const form = document.createElement("form");
        form.action = "/upload";
        form.method = "post";
        form.enctype = "multipart/form-data";

        // Create the first file input
        const label1 = document.createElement("label");
        label1.textContent = "Upload the main photo:";
        const fileInput1 = document.createElement("input");
        fileInput1.type = "file";
        fileInput1.id = "image1";
        fileInput1.name = "image1";
        fileInput1.accept = "image/*";
        fileInput1.required = true;
        fileInput1.textContent = "Upload the first Image"
        form.appendChild(label1);
        form.appendChild(fileInput1);

        // Create the second file input
        const label2 = document.createElement("label");
        label2.textContent = "Upload the watermark:";
        const fileInput2 = document.createElement("input");
        fileInput2.type = "file";
        fileInput2.id = "image2";
        fileInput2.name = "image2";
        fileInput2.accept = "image/*";
        fileInput2.required = true;
        fileInput2.textContent = "Upload the first Image"
        form.appendChild(label2);
        form.appendChild(fileInput2);

        // Create the submit button
        const submitInput = document.createElement("input");
        submitInput.type = "submit";
        submitInput.value = "Upload";
        form.appendChild(submitInput);

        // Append the form to the document body or any other desired location
        parentDiv.appendChild(form);

    }else{
        //create the form
        const form = document.createElement("form");
        form.action = "/upload";
        form.method = "post"; // You can set the method as needed
        form.enctype = "multipart/form-data"

        // Create the first file input
        const label1 = document.createElement("label");
        label1.textContent = "Upload the photo:";
        const fileInput = document.createElement("input");
        fileInput.type = "file";
        fileInput.id = "image";
        fileInput.name = "image";
        fileInput.accept = "image/*";
        fileInput.required = true;
        fileInput.textContent = "Upload the first Image"
        form.appendChild(label1);
        form.appendChild(fileInput);

        // Create the submit button
        const submitInput = document.createElement("input");
        submitInput.type = "submit";
        submitInput.value = "Upload";
        form.appendChild(submitInput);

        // Append the form to the document body or any other desired location
        parentDiv.appendChild(form);

    }

}

//send the selected process to the server
async function postData(option) {
    const data = {
        process: option
    };
    try {
        const response = await fetch('/option', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(data)
        });

        const responseData = await response.json();
        console.log(responseData.status);
    } catch (error) {
        // Handle network or other errors
        console.error("An error occurred:", error);
    }
}

window.onload = Init;
