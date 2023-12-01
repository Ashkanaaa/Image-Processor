from flask import Flask, redirect, url_for, render_template, request, session, jsonify
from datetime import timedelta
import uuid
import subprocess
import os
import imghdr
import convertapi


application = Flask(__name__)
application.secret_key = "_image_app" #This is just neccessary when using sessions 
application.permanent_session_lifetime = timedelta(minutes=5)
application.config['UPLOAD_FOLDER'] = 'static\\DB' #the directory where all the images are stored
DB = application.config['UPLOAD_FOLDER'] 
convertapi.api_secret = 'JVLmwq5qrxRV0rrw'

Process_Map = {
    'Grayscale':'1',
    'Spotlight': '2',
    'Watermark':'3',
    'Scramble':'4',
    'Unscramble':'5'
}

@application.route("/")
def home():
    return render_template("index.html")

@application.route("/example", methods=["GET"])
def example():
    return render_template("example.html")

#endpoint for reciving the process choosen by the client
@application.route("/option",  methods=["POST"])
def option():
    if request.method == "POST":
        data = request.get_json()
        option = data.get('process', 'Unknown')
        if option != "Unknown":
            session['process'] = option #assigning the process to the session
            respone = {"status":"Successful"} #returning sucess response
        else:
            respone = {"status":"Unsuccessful"}
        return jsonify(respone)

#endpoint for handling image upload from the client
@application.route("/upload", methods=["POST"])
def process_image():
    if request.method == "POST":
        session['id'] = str(uuid.uuid4()) #assigning uuid to the session
        print('UUID:'+ session['id'])

        #Spotlight
        if session['process'] == 'Spotlight':
            resultPath = spotlight(session, request)
            if resultPath is None:
                return 'no file part'
            else:
                return render_template('upload.html', image=resultPath + '/result.png')
            
        #Watermark
        if session['process'] == 'Watermark':
            resultPath = watermark(session, request)
            if resultPath is None:
                return 'no file part'
            else:
                return render_template('upload.html', image=resultPath + '/result.png')
            
        #Other Processes
        if session['process'] == 'Grayscale' or session['process'] == 'Scramble' or session['process'] == 'Unscramble':
            resultPath = other_processes(session, request)
            if resultPath is None:
                return 'no file part'
            else:
                return render_template('upload.html', image=resultPath + '/result.png')
        else:
            return 'No valid process'

#hadling the spotlight process
def spotlight(session, request):
    if 'image' not in request.files:
        return None
    img = request.files['image']
    if img.filename == '':
        return 'No Selected image'
    xCoordinate = request.form['xCoordinate']
    yCoordinate = request.form['yCoordinate']
    if img:
        # Generating the source directory based on the session UUID
        sourcePath = os.path.join(DB, session['id'], 'source')
        
        # Generating the result directory based on the session UUID
        resultPath = os.path.join(DB, session['id'], 'result')
        
        # Creating source and result directories if they do not exist
        os.makedirs(sourcePath)
        os.makedirs(resultPath)
        
        # Generating the image path by combining the source folder and the file name
        imgPath = os.path.join(sourcePath, img.filename)
        
        # Saving the uploaded image in the source directory
        img.save(imgPath)
        
        # Checking if the uploaded image is in JPEG format
        if imghdr.what(sourcePath + '\\' + img.filename) == 'jpeg' or imghdr.what(sourcePath + '\\' + img.filename) == 'jpg':
            # Converting the JPEG image to PNG
            jpg_to_png(imgPath, sourcePath)
            
            # Obtaining the name of the converted PNG file
            pngName = get_png_name(img.filename)
            
            # Generating the new image path for the converted PNG file
            imgPath = os.path.join(sourcePath, pngName)
        
        # Generating the command to process the image
        subprocess.run(['.\\app', Process_Map[session['process']], imgPath, resultPath, xCoordinate, yCoordinate], shell=True)
        
        # Returning the path to the result directory
        return resultPath

#handling the watermark process
def watermark(session, request):
    if 'image1' not in request.files or 'image2' not in request.files:
        return None
    img1 = request.files['image1']
    img2 = request.files['image2']
    if img1.filename == '' or img2.filename == '':
        return 'No Selected image'
    if img1 and img2:
        # Generating the source directory based on the session UUID
        sourcePath = os.path.join(DB, session['id'], 'source')
        
        # Generating the result directory based on the session UUID
        resultPath = os.path.join(DB, session['id'], 'result')
        
        # Creating source and result directories if they do not exist
        os.makedirs(sourcePath)
        os.makedirs(resultPath)
        
        # Generating the image paths by combining the source folder and the file names
        img1Path = os.path.join(sourcePath, img1.filename)
        img2Path = os.path.join(sourcePath, img2.filename)
        
        # Saving the uploaded images in the source directory
        img1.save(img1Path)
        img2.save(img2Path)
        
        # Checking if the first uploaded image is in JPEG format
        if imghdr.what(sourcePath + '\\' + img1.filename) == 'jpeg' or imghdr.what(sourcePath + '\\' + img1.filename) == 'jpg':
            # Converting the JPEG image to PNG
            jpg_to_png(img1Path, sourcePath)
            
            # Obtaining the name of the converted PNG file
            png1Name = get_png_name(img1.filename)
            
            # Generating the new image path for the converted PNG file
            img1Path = os.path.join(sourcePath, png1Name)
        
        # Checking if the second uploaded image is in JPEG format
        if imghdr.what(sourcePath + '\\' + img2.filename) == 'jpeg' or imghdr.what(sourcePath + '\\' + img2.filename) == 'jpg':
            # Converting the JPEG image to PNG
            jpg_to_png(img2Path, sourcePath)
            
            # Obtaining the name of the converted PNG file
            png2Name = get_png_name(img2.filename)
            
            # Generating the new image path for the converted PNG file
            img2Path = os.path.join(sourcePath, png2Name)
        
        # Generating the command to process the images
        subprocess.run(['.\\app', Process_Map[session['process']], img1Path, img2Path, resultPath], shell=True)
        
        # Returning the path to the result directory
        return resultPath
    
#handling other processes
def other_processes(session, request):
    if 'image' not in request.files:
        return None
    img = request.files['image']
    if img.filename == '':
        return 'No Selected image'
    if img:
        # Generating the source directory based on the session UUID
        sourcePath = os.path.join(DB, session['id'], 'source')
        
        # Generating the result directory based on the session UUID
        resultPath = os.path.join(DB, session['id'], 'result')
        
        # Creating source and result directories if they do not exist
        os.makedirs(sourcePath)
        os.makedirs(resultPath)
        
        # Generating the image path by combining the source folder and the file name
        imgPath = os.path.join(sourcePath, img.filename)
        
        # Saving the uploaded image in the source directory
        img.save(imgPath)
        
        # Checking if the uploaded image is in JPEG format
        if imghdr.what(sourcePath + '\\' + img.filename) == 'jpeg' or imghdr.what(sourcePath + '\\' + img.filename) == 'jpg':
            # Converting the JPEG image to PNG
            jpg_to_png(imgPath, sourcePath)
            
            # Obtaining the name of the converted PNG file
            pngName = get_png_name(img.filename)
            
            # Generating the new image path for the converted PNG file
            imgPath = os.path.join(sourcePath, pngName)
        
        # Generating the command to process the image
        subprocess.run(['.\\app', Process_Map[session['process']], imgPath, resultPath], shell=True)
        
        # Returning the path to the result directory
        return resultPath
    
#Converts a given file name to a PNG file name by extracting the part before the dot and appending '.png'.
def get_png_name(fileName):
    pngName = fileName.split('.')
    return str(pngName[0]) + '.png'

#Converts a JPEG image to PNG format using ConvertAPI.
def jpg_to_png(imgPath, sourcePath):
    convertapi.convert('png', {
        'File': imgPath
    }, from_format = 'jpg').save_files(sourcePath)

if __name__=="__main__":
    application.run(debug=True)
